
----
### Twitter Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 677.743 | 0.186773 | 5016.59ms | 264040 | 160 | 7.70477e+07 | 371539 | 0.115545 | 1(Win) | true |
| simdjson (ondemand) | 274.56 | 0.309972 | 5865.54ms | 264040 | 40 | 3.23274e+08 | 917133 | 0.199043 | 2(Loss) | true |
