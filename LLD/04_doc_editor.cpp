// APPROACHES: - top down: top level objects are created first
//             - bottom up: bottom level objects are created first

// Principle of Least Knowledge

// Document Editor LLD Example
// A simple design for a text editor system:
// - Document holds text and version history
// - Editor handles user actions like typing, deleting, undo, save
// - Storage backend saves/loads the document
// - Formatting tools can apply styling without changing editor logic

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Document
{
private:
    string title;
    string content;
    vector<string> history;

public:
    Document(string t, string c = "") : title(t), content(c)
    {
        history.push_back(content);
    }

    void insertText(const string& text)
    {
        content += text;
        history.push_back(content);
    }

    void deleteText(int count)
    {
        if (count > 0 && count <= (int)content.length())
        {
            content.erase(content.length() - count);
            history.push_back(content);
        }
    }

    void undo()
    {
        if (history.size() > 1)
        {
            history.pop_back();
            content = history.back();
        }
    }

    string getContent() const { return content; }
    string getTitle() const { return title; }
};

class Storage
{
public:
    virtual void save(const Document& document) = 0;
    virtual ~Storage() = default;
};

class FileStorage : public Storage
{
public:
    void save(const Document& document) override
    {
        cout << "Saving document '" << document.getTitle() << "' to file\n";
        cout << "Content: " << document.getContent() << "\n";
    }
};

class CloudStorage : public Storage
{
public:
    void save(const Document& document) override
    {
        cout << "Saving document '" << document.getTitle() << "' to cloud\n";
    }
};

class FormattingTool
{
public:
    virtual void apply(Document& document) = 0;
    virtual ~FormattingTool() = default;
};

class BoldFormatter : public FormattingTool
{
public:
    void apply(Document& document) override
    {
        string current = document.getContent();
        document.insertText("**");
        // In a real editor, format selection or add markup around selected text.
        cout << "Applied bold formatting to: " << current << "\n";
    }
};

class Editor
{
private:
    Document document;
    Storage& storage;
    vector<FormattingTool*> tools;

public:
    Editor(Document doc, Storage& s) : document(doc), storage(s) {}

    void addTool(FormattingTool* tool)
    {
        tools.push_back(tool);
    }

    void type(const string& text)
    {
        document.insertText(text);
    }

    void deleteText(int count)
    {
        document.deleteText(count);
    }

    void undo()
    {
        document.undo();
    }

    void applyFormatting()
    {
        for (FormattingTool* tool : tools)
        {
            tool->apply(document);
        }
    }

    void save()
    {
        storage.save(document);
    }

    void printDocument()
    {
        cout << "Current content: " << document.getContent() << "\n";
    }
};

int main()
{
    Document doc("Notes", "Hello ");
    FileStorage fileStorage;
    Editor editor(doc, fileStorage);

    editor.type("World");
    editor.printDocument();

    BoldFormatter bold;
    editor.addTool(&bold);
    editor.applyFormatting();

    editor.save();
    editor.undo();
    editor.printDocument();

    return 0;
}