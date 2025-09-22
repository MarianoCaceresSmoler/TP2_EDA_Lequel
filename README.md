# EDA #level2: Lequel?

## Integrantes del grupo y contribución al trabajo de cada integrante

* Mariano Caceres Smoler: armado de codigo base de las funciones, optimizacion del calculo de trigramas y documentacion.
* Sofia Capiel: implementacion de threads, integracion de nuevos lenguajes y testeo.

## Respuestas del enunciado

1. ¿En qué idioma está el siguiente texto? UCRANIANO

історія земель сучасної України, українського народу та інших національностей, що проживають на території України, від доісторичних часів до сьогодення.


2. ¿En qué idioma está el siguiente texto? COREANO

아리랑, 아리랑, 아라리요... 아리랑 고개로 넘어간다. 나를 버리고 가시는 님은 십리도 못가서 발병난다. 청천하늘엔 잔별도 많고, 우리네 가슴엔 희망도 많다. 저기 저 산이 백두산이라지, 동지 섣달에도 꽃만 핀다.


3. ¿En qué idioma está el siguiente texto? BIRMANO

၁၉၄၀ ခုနှစ်တွင် ဗိုလ်ချုပ်အောင်ဆန်းဦးဆောင်သည့် ရဲဘော်သုံးကျိပ်အဖွဲ့ဝင်တို့သည် ဗမာ့လွတ်မြောက်ရေးတပ်မတော် (ဘီအိုင်အေ) ကို တည်ထောင်ခဲ့ကြသည်။[၂၀][၂၀] ရဲဘော်သုံးကျိပ်သည် ဂျပန်နိုင်ငံတွင် စစ်သင်တန်းများတက်ရောက်ခဲ့ကြသည်။[၂၀]


4. ¿En qué idioma está el siguiente texto? SUAJILI

Negema wangu binti, mchachefu wa sanati upulike wasiati asa ukanzingatia. Maradhi yamenshika hatta yametimu mwaka sikupata kutamka neno lema kukwambia. Ndoo mbee ujilisi na wino na qaratasi moyoni nina hadithi nimependa kukwambia.


5. ¿En qué idioma está el siguiente texto? ARMENIO

Այժմ նա յուր կինտոյի արհեստով ժառանգած Ճանճուր մականունը կցելով յուր հոր՝ Օհանեսի անվան հետ, կոչվում է «Թիֆլիսի պատվավոր քաղաքացի Ճանճուր Իվանիչ»։ Այդ անունով ևս մենք պարտավորվում ենք նրան ծանոթացնել մեր ընթերցողներին։


6. ¿En qué idioma está el siguiente texto? TURCO

Belirli bir bölgedeki mevcut hava durumu hava raporu, gelecekte beklenen durumlar ise hava tahmini şeklinde, ilgili meteoroloji otoriteleri tarafından yayımlanır.


7. ¿En qué idioma está el siguiente texto? CHEROQUI

ᎤᎵᏍᏔᏴᏗ ᎦᎵᏙᏗ ᏭᎷᏤᎢ, ᎤᏗᏔᎮ ᎦᏁᎲ, ᎤᏲᏏᏍᎩ ᎤᏗᏔᎮ ᎤᏅᏗ ᏃᎴ ᎤᎩᏍᏙᎡ ᏑᎾᎴ ᎠᎩᏍᏗ ᎤᏂᏑᎸᏓ. ᎣᏍᏓ ᏄᎵᏍᏔᏁᎮ ᎤᏩᏌ ᎤᏪᏅᏒ ᎡᏙᎲ. ᎦᏅᏆᎶᏍᏗ ᏭᏴᎮ ᏣᏄᏏ ᏃᎴ ᏣᏁᎳ ᎠᏂᏎᏂᏏ ᏴᎩ, ᎣᏍᏓ ᏄᏩᏁᎴ ᎠᏦᏴ.


8. ¿En qué idioma está el siguiente texto? ARABE

ُیعتقد بأن ضابطة في الجیش البریطاني تدعى بریت تشاندي أصبحت أولامرأة من أصول آسیویة ُتكملُ رحلة استكشافیة فردیة عبر .القارة القطبیة الجنوبی  


9. ¿En qué idioma está el siguiente texto? GUYARATI

ગુજરાતી સંસ્કૃત ભાષામાંથી વિકસિત થયેલી આધુનિક ઈન્ડો-આર્યન ભાષા છે. પરંપરાગત રીતે ૩ ઐતિહાસિક તબક્કાઓ પ્રમાણે ઈન્ડો-આર્યન ભાષાઓ વચ્ચે ભેદ કરાય છે.


10. ¿En qué idioma está el siguiente texto? ITALIANO

Al Seicento appartiene il primo trattato dedicato non ai volgari italiani o a uno o più di tali volgari, ma alla lingua italiana in quanto tale: Delle osservazioni della lingua italiana di Marcantonio Mambelli, detto il Cinonio.


11. El siguiente texto fue escrito por Robert Burns en escocés. ¿Qué dice Lequel? ¿Qué falla? Justifica por qué ocurre lo que ocurre.

And there's a hand, my trusty fiere! and gie's a hand o' thine! And we’ll tak' a right gude-willie waught, for auld lang syne.

Lequel dice que el texto esta en ingles, no en escoces. Esto se debe a varios razones:
- En primer lugar, el escocés es una variedad de lengua germánica occidental descendiente del inglés medio temprano; de esta forma, el escocés y el ingles comparten muchas palabras (comohand, there, right, etc.).
- En segundo lugar, en este fragmento de text hay pocas palabras claramente escocesas (como gude-willie o gie' por ejemplo), en comparacion con las que hay que coinciden con el ingles. Y como los trigramas se forman a partir de secuencias de letras, la mayoría de los trigramas del texto van a coincidir con trigramas frecuentes en inglés.
- Por ultimo, hay que tener en cuenta la frecuencia de los trigramas en los datasets de cada idioma. El trigrama con mas frecuencia del perfil escoces tiene la misma frecuencia que el trigrama 734 del ingles, para poner en perspectiva. Teniendo esto en cuenta, las palabras del ingles incluidas en el fragmento van a tener mucho mas peso que las presentes que son caracteristicas del escoces.


12. El siguiente texto está en inglés. ¿Qué dice Lequel? ¿Qué falla? Justifica por qué ocurre lo que ocurre.

IT WAS THE BEST OF TIMES, IT WAS THE WORST OF TIMES,
IT WAS THE AGE OF WISDOM, IT WAS THE AGE OF FOOLISHNESS,
IT WAS THE EPOCH OF BELIEF, IT WAS THE EPOCH OF INCREDULITY,
IT WAS THE SEASON OF LIGHT, IT WAS THE SEASON OF DARKNESS,
IT WAS THE SPRING OF HOPE, IT WAS THE WINTER OF DESPAIR,
WE HAD EVERYTHING BEFORE US, WE HAD NOTHING BEFORE US,
WE WERE ALL GOING DIRECT TO HEAVEN, WE WERE ALL GOING DIRECT THE OTHER WAY
– IN SHORT, THE PERIOD WAS SO FAR LIKE THE PRESENT PERIOD, THAT SOME OF ITS NOISIEST AUTHORITIES INSISTED ON ITS BEING RECEIVED, FOR GOOD OR FOR EVIL, IN THE SUPERLATIVE DEGREE OF COMPARISON ONLY.

Lequel dice que el texto esta en afrikaans, no en ingles.
- Como en el caso de ingles y escoces, afrikaans e inglés comparten muchos elementos léxicos y estructurales (como las palabras it, was, etc.).
- Por otro lado, palabras como IT, WAS, o THE aparecen muchisimas veces en el fragmento, lo que puede inclinar la balanza hacia el perfil de idioma que tenga una mayor frecuencia en esas palabras en particular.
- Por ultimo, el texto esta en mayusculas, mientras que los perfiles de lenguajes estan en minusculas. El algoritmo implementado no normaliza mayusculas a minusculas, sino que guarda los caracteres tal cual estan en el texto ingresado. Y por esto, el programa terminara generando un perfil de trigramas que no coincide como deberia con los guardados.

Teniendo este problema en cuenta, decidimos agregar el normalizado de los trigramas a minuscula. Luego de esto, Lequel ahora si dice que el texto esta en ingles.

## Bonus points

- Hicimos normalizado de textos a minusculas para arreglar el error de cuando ingresas textos en mayusculas.
- Metimos como lenguajes adicionales: Catalan y C. Los textos con los que cargamos los trigramas para estos lenguajes estan en resources/extra_languages.

Por otro lado, en cuanto al cuello de botella computacional con textos grandes, notamos que este se produce en la funcion de getCosineSimilarity. Por cada idioma se recorre todo el perfil de trigramas del texto, y por cada trigrama se ejecuta la funcion find de map. Si el texto ingresado es muy grande, entonces el perfil del texto tendra muchisimos trigramas, y con estos crecera el costo del bucle. De esta forma, la complejidad de calculo por cada texto termina siendo 
O(N x M), siendo N el numero de trigramas del texto y M el numero de lenguajes (que, si bien se mantiene constante, no deja de ser un multiplicador).

Para solucionar este problema implementamos varias optimizaciones:
- Uso de unordered_map en lugar de map: esto nos da la mayor velocidad de búsqueda posible. Mientras que map tiene una complejidad promedio de O(log n) por busqueda, unordered_map ofrece O(1) en promedio. De esta forma, aceleramos significativamente la comparacion en grandes volúmenes de datos.
- Limite de trigramas procesados: establecimos un maximo de 2000 trigramas por texto, dado que los perfiles de los lenguajes cargados en resources tambien rondan esa magnitud. Esto evita que textos extremadamente largos inflen el costo de procesamiento sin aportar mejoras sustanciales en la identificacion.
- Cotas de similitud coseno: en la función getCosineSimilarity, a medida que se comparan trigramas, se calcula el maximo porcentaje de coincidencia posible con los trigramas que faltan por recorrer. Si ese maximo ya es inferior al minimo requerido (20% de coincidencia), el bucle se corta de forma anticipada evitando asi comparaciones innecesarias.
- Paralelizacion con threads: dividimos los perfiles de lenguajes entre multiples hilos para aprovechar la concurrencia y reducir el tiempo total de comparación.

Con estas optimizaciones, la complejidad efectiva deja de ser estrictamente O(N x M). Ahora:
- El uso de unordered_map reduce la busqueda a O(1) promedio, en lugar de O(log n).
- El limite de trigramas fija N ≤ 2000, por lo que la comparacion ya no crece indefinidamente con el tamaño del texto.
- Las cotas permiten que, en la practica, muchos bucles corten de forma temprana.
- La paralelizacion distribuye el trabajo entre varios nucleos, acercando la complejidad practica a O(N × M / T), donde T es el número de threads disponibles en la maquina.

Asi, el programa paso de una complejidad teorica O(N × M) a una complejidad cercana a O(M × 2000 / T) en el peor caso, teniendo en cuenta los escapes tempranos que en muchas ocasiones reducen aun más el tiempo de ejecución.
