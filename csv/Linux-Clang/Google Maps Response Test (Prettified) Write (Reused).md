
----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16239.5 | 0.0833389 | 920.286ms | 31235 | 4890 | 11427.3 | 1834.29 | 0.0434795 | 0.317867 | 1.40173 | 0.258844 | 6.34939e-05 | 6.76971e-06 | 2.154e-06 | 1(Win) | true |
| Glaze | 5647 | 0.0919102 | 1268.51ms | 31235 | 1280 | 30087.3 | 5275.01 | 0.0836004 | 0.902999 | 3.58447 | 0.627565 | 0.00229718 | 1.36566e-05 | 5.45262e-06 | 2(Loss) | true |
