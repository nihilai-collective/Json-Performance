
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 222.216 | 1.49499 | 5726.75ms | 1834197 | 40 | 5.53962e+11 | 7.87174e+06 | 2.18193 | 11.1413 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 218.909 | 0.642539 | 6050.26ms | 1834197 | 30 | 7.90836e+10 | 7.99067e+06 | 0.0138514 | 11.3098 | 1(Tie) | true |
