
----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 10922.8 | 1.99737 | 485.605ms | 56369 | 320 | 3.09227e+06 | 4921.6 | 0.291734 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 10529.2 | 0.521677 | 587.518ms | 56369 | 320 | 227011 | 5105.6 | 1.6242 | 1(Tie) | true |
| Glaze | 2705.48 | 0.228541 | 1938.32ms | 56369 | 4890 | 1.00839e+07 | 19869.9 | 1.30361 | 3(Loss) | true |
