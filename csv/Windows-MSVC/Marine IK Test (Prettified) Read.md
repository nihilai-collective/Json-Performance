
----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13012.1 | 0.179294 | 6883.8ms | 7351818 | 640 | 5.97319e+08 | 538824 | 0.703875 | 0.233475 | 1(Win) | true |
| simdjson (stage-1) | 11947.4 | 0.216927 | 7533.54ms | 7351818 | 80 | 1.29645e+08 | 586841 | 0.164497 | 0.254286 | 2(Loss) | true |
