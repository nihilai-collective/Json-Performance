
----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 1033.27 | 0.123837 | 10089.1ms | 7351818 | 40 | 2.82438e+09 | 6.7855e+06 | 5.08159 | -(Win) | false |
| simdjson (ondemand) | 698.543 | 0.145884 | 7024.11ms | 7351818 | 40 | 8.57583e+09 | 1.0037e+07 | 1.20448 | 2(Loss) | true |
