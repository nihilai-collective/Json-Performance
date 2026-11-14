
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 353.364 | 1.46493 | 8124.98ms | 1834197 | 30 | 1.57761e+11 | 4.95021e+06 | 1.74665 | 8.59994 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 340.952 | 1.20667 | 8230.96ms | 1834197 | 40 | 1.53299e+11 | 5.13041e+06 | 1.51453 | 8.91392 | 1(Tie) | true |
