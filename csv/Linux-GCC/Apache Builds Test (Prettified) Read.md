
----
### Apache Builds Test (Prettified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14456.9 | 0.083545 | 1544.33ms | 124597 | 160 | 7544.4 | 8219.24 | 0.0300452 | 0.358008 | 1.71319 | 0.0635249 | 1.64029e-05 | 1.58009e-05 | 1.41456e-05 | 1(Win) | true |
| simdjson (stage-1) | 14032.9 | 0.0578188 | 1563.67ms | 124597 | 640 | 15340.4 | 8467.57 | 0.00623664 | 0.368244 | 1.83555 | 0.0691992 | 1.5199e-05 | 2.33252e-06 | 1.1161e-06 | 2(Loss) | true |
