
----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 2237.44 | 0.112287 | 6433.25ms | 264040 | 320 | 5.11034e+06 | 112543 | 0.0747773 | 1.10624 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2232.58 | 0.0754216 | 6585.79ms | 264040 | 1280 | 9.26248e+06 | 112788 | 0.104176 | 1.10853 | 1(Tie) | true |
