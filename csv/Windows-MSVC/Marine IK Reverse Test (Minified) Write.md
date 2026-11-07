
----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 877.05 | 0.439782 | 6232.81ms | 1834197 | 30 | 2.30802e+09 | 1.99444e+06 | 0.53212 | 2.8227 | 1(Win) | true |
| Glaze | 612.971 | 0.638143 | 8798.7ms | 1833577 | 160 | 5.30243e+10 | 2.85272e+06 | 1.56377 | 4.03892 | 2(Loss) | true |
