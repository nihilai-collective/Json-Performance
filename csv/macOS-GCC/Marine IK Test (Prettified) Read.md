
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1730.16 | 0.718833 | 6287.14ms | 7351818 | 30 | 2.54562e+10 | 4.05236e+06 | 0.422728 | 1(Win) | true |
| Jsonifier | 1656.68 | 0.606368 | 5929.02ms | 7351818 | 30 | 1.97563e+10 | 4.2321e+06 | 0.99771 | 2(Loss) | true |
| simdjson (reflection) | 1609.56 | 0.916595 | 6431.02ms | 7351818 | 30 | 4.78247e+10 | 4.356e+06 | 0.109387 | 3(Loss) | true |
| simdjson (ondemand) | 1410.93 | 0.565913 | 7763.59ms | 7351818 | 80 | 6.32654e+10 | 4.96923e+06 | 1.71527 | 4(Loss) | true |
| Glaze | 1331.9 | 0.981261 | 7635.88ms | 7351818 | 80 | 2.13454e+11 | 5.26409e+06 | 2.41579 | 5(Loss) | true |
