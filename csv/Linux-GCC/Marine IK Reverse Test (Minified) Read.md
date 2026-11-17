
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 869.392 | 0.143482 | 6424.59ms | 1834197 | 80 | 6.66728e+08 | 2.01201e+06 | 2.71491 | 2.84774 | -(Win) | false |
| Jsonifier (two-stage) | 746.528 | 0.0747534 | 7339ms | 1834197 | 80 | 2.45444e+08 | 2.34315e+06 | 0.903896 | 3.31643 | 2(Loss) | true |
| Glaze | 657.36 | 0.0877353 | 8335.18ms | 1834197 | 160 | 8.72076e+08 | 2.66099e+06 | 0.433706 | 3.76629 | 3(Loss) | true |
| simdjson (reflection) | 621.466 | 0.0499164 | 8851.33ms | 1834197 | 160 | 3.15838e+08 | 2.81468e+06 | 0.0579789 | 3.98382 | 4(Loss) | true |
| simdjson (ondemand) | 565.21 | 0.256811 | 9850.81ms | 1834197 | 30 | 1.89506e+09 | 3.09483e+06 | 0.681529 | 4.38034 | 5(Loss) | true |
