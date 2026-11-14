
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 961.528 | 0.171652 | 5861.16ms | 94653 | 1280 | 3.32393e+07 | 93879.9 | 0.39183 | 2.57411 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 958.059 | 0.200782 | 5761.18ms | 94653 | 2560 | 9.16164e+07 | 94219.8 | 0.245791 | 2.58339 | 1(Tie) | true |
