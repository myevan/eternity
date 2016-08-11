#pragma once

class JsonWriter
{
private:
    size_t m_itemCount;
    size_t m_bufSize;
    char m_buf[32]; // {}

public:
    JsonWriter()
    {
        m_itemCount = 0;
        m_bufSize = 0;
        m_buf[0] = '\0';
    }
    
    JsonWriter& Begin()
    {
        AddChar('{');
        return *this;
    }

    JsonWriter& End()
    {
        if (sizeof(m_buf) <= m_bufSize + 1)
        {
            m_buf[m_bufSize] = '\0';
            m_buf[m_bufSize - 1] = '.';
            m_buf[m_bufSize - 2] = '.';
            m_buf[m_bufSize - 3] = '.';
            puts(m_buf);
        }
        else
        {
            AddChar('}');
        }

        return *this;
    }

    JsonWriter& Add(const char* key, int value)
    {
        AddComma();
        AddText(key);
        AddChar(':');
        AddInteger(value);
        
        m_itemCount++;
        return *this;
    }

    JsonWriter& Add(const char* key, const char* value)
    {
        AddComma();
        AddText(key);
        AddChar(':');
        AddText(value);

        m_itemCount++;
        return *this;
    }

    operator const char*()
    {
        return m_buf;
    }

public:
    bool HasSlack(int inSize)
    {
        if (sizeof(m_buf) < m_bufSize + inSize + 1)  // } \0
            return false;
        else
            return true;
    }

    void AddComma()
    {
        if (0 < m_itemCount)
        {
            AddChar(',');
        }
    }

    void AddChar(const char ch)
    {
        if (!HasSlack(sizeof(ch)))
            return;

        m_buf[m_bufSize++] = ch;
        m_buf[m_bufSize] = '\0';
    }

    void AddText(const char* text)
    {
        size_t textSize = strlen(text);
        if (!HasSlack(textSize + 2)) // ""
            return;

        m_buf[m_bufSize++] = '"';
        memcpy(m_buf + m_bufSize, text, textSize);
        m_bufSize += textSize;
        m_buf[m_bufSize++] = '"';
        m_buf[m_bufSize] = '\0';
    }

    void AddInteger(int num)
    {
        if (!HasSlack(sizeof(char)))
            return;

        int slackSize = sizeof(m_buf) - m_bufSize;
        int numLen = snprintf(m_buf + m_bufSize, slackSize, "%d", num);
        if (0 < numLen)
        {
            m_bufSize += numLen;
        }
        m_buf[m_bufSize] = '\0';
    }

};

