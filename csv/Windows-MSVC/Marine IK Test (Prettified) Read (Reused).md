
----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1385.69 | 0.672375 | 8000.27ms | 7351818 | 80 | 9.25917e+10 | 5.05975e+06 | 1.25296 | 2.19324 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE DID NOT CONVERGE | 1365.2 | 0.859548 | 8041.59ms | 7351818 | 80 | 1.55892e+11 | 5.13567e+06 | 3.65707 | 2.22613 | -(Tie) | false |
