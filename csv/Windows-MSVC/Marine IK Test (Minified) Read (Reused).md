
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 382.677 | 0.862703 | 7310.32ms | 1834197 | 40 | 6.22028e+10 | 4.57102e+06 | 0.204053 | 7.94214 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 381.643 | 0.490121 | 7255.88ms | 1834197 | 80 | 4.03715e+10 | 4.58342e+06 | 1.37518 | 7.96339 | 1(Tie) | true |
