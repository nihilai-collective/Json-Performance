
----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6482.1 | 0.434569 | 9208ms | 9930848 | 30 | 1.20943e+09 | 1.46107e+06 | 0.28348 | 1(Win) | true |
| Glaze | 3190.18 | 0.190093 | 9280.54ms | 9930228 | 160 | 5.09497e+09 | 2.96855e+06 | 0.23568 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 268.162 | 0.624895 | 10100.8ms | 10018896 | 30 | 1.48724e+12 | 3.56305e+07 | 16.2895 | -(Loss) | false |
