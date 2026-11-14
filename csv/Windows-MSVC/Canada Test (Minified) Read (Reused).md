
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 428.358 | 1.09456 | 7631.41ms | 2090234 | 40 | 1.03779e+11 | 4.65358e+06 | 0.572355 | 7.09508 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 418.299 | 0.827899 | 7940.57ms | 2090234 | 80 | 1.24526e+11 | 4.76549e+06 | 1.99693 | 7.26565 | 1(Tie) | true |
