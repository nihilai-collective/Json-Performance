
----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13272.4 | 0.0448569 | 6710.97ms | 7351818 | 640 | 3.59359e+07 | 528257 | 0.0444465 | 0.228891 | 1(Win) | true |
| simdjson (stage-1) | 12176 | 0.0781857 | 7313.43ms | 7351818 | 160 | 3.24308e+07 | 575826 | 0.0180143 | 0.249518 | 2(Loss) | true |
