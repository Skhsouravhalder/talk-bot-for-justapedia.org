import pywikibot
from transformers import pipeline

def paraphrase_text(text):
    # Initialize the paraphrase pipeline
    paraphraser = pipeline("text2text-generation", model="tuner007/pegasus_paraphrase")

    # Split text into manageable chunks
    sentences = text.split('. ')
    paraphrased_sentences = []

    for sentence in sentences:
        if sentence.strip():
            paraphrase = paraphraser(sentence, max_length=60, num_return_sequences=1)
            paraphrased_sentences.append(paraphrase[0]['generated_text'])

    # Combine paraphrased sentences back into text
    return '. '.join(paraphrased_sentences)

def rewrite_article(page_title):
    # Site and page setup
    site = pywikibot.Site('justawiki', 'justawiki')
    page = pywikibot.Page(site, page_title)

    try:
        # Fetch the current content of the page
        content = page.text

        # Rewrite the content using paraphrasing
        new_content = paraphrase_text(content)

        # Save the changes to the page
        page.text = new_content
        page.save(f'Rewrote entire article: Paraphrased content to avoid copyright issues')

        print(f'Successfully rewrote the article: {page_title}')

    except pywikibot.exceptions.Error as e:
        print(f'Error rewriting the article: {e}')

if __name__ == "__main__":
    # Example usage
    rewrite_article('Garth Williams')
