
----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1615.92 | 0.462515 | 7046.27ms | 7351818 | 40 | 1.61088e+10 | 4.33886e+06 | 0.993578 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 1612.27 | 1.14411 | 6960.13ms | 7351818 | 30 | 7.42627e+10 | 4.34866e+06 | 1.573 | 1(Tie) | true |
