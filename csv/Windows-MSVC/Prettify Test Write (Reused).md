
----
### Prettify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4522.72 | 0.377917 | 7719.28ms | 699405 | 160 | 4.97018e+07 | 147479 | 0.1613 | 0.547304 | 1(Win) | true |
| Glaze | 2908.13 | 0.248859 | 6007.11ms | 699405 | 160 | 5.21263e+07 | 229359 | 0.500622 | 0.85124 | 2(Loss) | true |
| simdjson (ondemand) | 1376.09 | 0.172931 | 6755.68ms | 767297 | 640 | 5.41202e+08 | 531761 | 0.308104 | 1.79869 | 3(Loss) | true |
