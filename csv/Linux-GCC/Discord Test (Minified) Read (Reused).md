
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1643.13 | 0.107996 | 3631.14ms | 56369 | 1280 | 1.59794e+06 | 32716.7 | 0.168477 | 1.50555 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 1637.56 | 0.304464 | 3738.17ms | 56369 | 160 | 1.59838e+06 | 32828 | 0.541462 | 1.51065 | 1(Tie) | true |
