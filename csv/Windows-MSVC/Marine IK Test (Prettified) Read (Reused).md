
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1350.48 | 0.704207 | 8376.39ms | 7351818 | 80 | 1.06932e+11 | 5.19168e+06 | 2.13268 | 2.25048 | 1(Win) | true |
| Jsonifier (generic) | 1283.41 | 0.89173 | 8816.33ms | 7351818 | 40 | 9.49256e+10 | 5.46296e+06 | 0.08797 | 2.36801 | 2(Loss) | true |
