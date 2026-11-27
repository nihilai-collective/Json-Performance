
----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1331.49 | 0.0241824 | 2135.67ms | 18245 | 4890 | 48833.5 | 13067.9 | 0.314039 | 3.87053 | 16.9158 | 3.58772 | 0.00439227 | 4.44193e-05 | 2.49949e-05 | 1(Win) | true |
| simdjson (ondemand) | 971.441 | 0.0190947 | 2623.38ms | 18245 | 4890 | 57199.4 | 17911.3 | 0.0511777 | 5.30016 | 27.5813 | 5.36015 | 0.00607462 | 3.23365e-05 | 1.69921e-05 | 2(Loss) | true |
