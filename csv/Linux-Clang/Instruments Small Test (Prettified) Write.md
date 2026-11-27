
----
### Instruments Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13720 | 0.369575 | 794.727ms | 9249 | 1280 | 7225.96 | 642.895 | 0.458769 | 0.399031 | 1.37582 | 0.240134 | 0.00014233 | 8.78473e-06 | 8.44686e-08 | 1(Win) | true |
| Glaze | 2654.98 | 0.131158 | 1067.66ms | 9249 | 4890 | 92846.9 | 3322.26 | 1.10664 | 1.95827 | 3.89123 | 0.651206 | 0.000416538 | 3.63053e-05 | 1.4416e-05 | 2(Loss) | true |
