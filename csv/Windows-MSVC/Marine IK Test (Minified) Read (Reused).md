
----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 381.038 | 0.751524 | 7455.71ms | 1834197 | 30 | 3.57078e+10 | 4.59069e+06 | 0.661842 | 7.97605 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 380.263 | 0.898536 | 7309.91ms | 1834197 | 30 | 5.12526e+10 | 4.60004e+06 | 0.638098 | 7.99252 | 1(Tie) | true |
