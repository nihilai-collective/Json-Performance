
----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4234.78 | 0.0941217 | 4343.68ms | 183677 | 4890 | 7.41202e+06 | 41364.2 | 0.513022 | 0.584271 | 1(Win) | true |
| Jsonifier (two-stage) | 4027.98 | 0.078698 | 4604.84ms | 183677 | 2560 | 2.99849e+06 | 43487.8 | 0.155146 | 0.614281 | 2(Loss) | true |
| Glaze | 2373.92 | 0.0547774 | 7582.79ms | 183677 | 1280 | 2.09118e+06 | 73788.7 | 0.206131 | 1.04256 | 3(Loss) | true |
| simdjson (ondemand) | 1114.49 | 0.112107 | 8166.34ms | 183677 | 160 | 4.9676e+06 | 157174 | 0.030709 | 2.22111 | 4(Loss) | true |
