
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1011.69 | 0.307222 | 5094.75ms | 7351818 | 30 | 1.35993e+10 | 6.93019e+06 | 0.860278 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 688.63 | 0.901432 | 7715.01ms | 7351818 | 40 | 3.36933e+11 | 1.01814e+07 | 6.74014 | -(Loss) | false |
