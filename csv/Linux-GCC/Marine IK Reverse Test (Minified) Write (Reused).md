
----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1229.9 | 0.0582352 | 9425.97ms | 1922245 | 160 | 1.2055e+08 | 1.49052e+06 | 0.171609 | 2.01293 | 1(Win) | true |
| simdjson (reflection) | 1038.04 | 0.0951736 | 5510.34ms | 1922245 | 40 | 1.13002e+08 | 1.76602e+06 | 1.05825 | 2.38503 | 2(Loss) | true |
| Glaze | 916.788 | 0.204563 | 6015.84ms | 1833577 | 30 | 4.56707e+08 | 1.90735e+06 | 0.563734 | 2.70047 | 3(Loss) | true |
