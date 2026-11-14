
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2864.06 | 0.0308489 | 1054.07ms | 9378 | 4890 | 4537.81 | 3122.69 | 0.00924031 | 1.82049 | 8.45468 | 1.44732 | 0.000970007 | 2.28748e-05 | 1.11212e-06 | 1(Win) | true |
| simdjson (ondemand) | 2391.92 | 0.0481395 | 1113.7ms | 9378 | 1280 | 4147.05 | 3739.07 | 0.0775569 | 2.17578 | 9.17402 | 1.56899 | 0.00116171 | 1.56617e-05 | 5.83147e-07 | 2(Loss) | true |
