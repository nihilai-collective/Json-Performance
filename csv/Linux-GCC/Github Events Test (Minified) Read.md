
----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16847.9 | 0.0423181 | 1023.35ms | 53331 | 4890 | 7980.52 | 3018.8 | 0.0745734 | 0.309743 | 1.50764 | 0.0627029 | 5.51174e-05 | 3.56611e-06 | 7.89912e-07 | 1(Win) | true |
| simdjson (stage-1) | 14912.6 | 0.0478919 | 1059.04ms | 53331 | 1280 | 3414.96 | 3410.56 | 0.0546715 | 0.350033 | 1.73931 | 0.0650843 | 5.46557e-05 | 2.43175e-06 | 1.46491e-07 | 2(Loss) | true |
