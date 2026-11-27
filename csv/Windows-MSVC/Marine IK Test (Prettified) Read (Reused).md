
----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE DID NOT CONVERGE | 820.696 | 0.608186 | 6804.12ms | 7351818 | 40 | 1.07984e+11 | 8.54304e+06 | 4.01178 | 3.01666 | -(Tie) | false |
| Jsonifier (generic) STATISTICAL TIE DID NOT CONVERGE | 804.424 | 1.45369 | 6894.74ms | 7351818 | 40 | 6.42134e+11 | 8.71586e+06 | 17.5046 | 3.07766 | -(Tie) | false |
