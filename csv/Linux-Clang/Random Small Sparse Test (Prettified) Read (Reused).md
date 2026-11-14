
----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3994.57 | 0.0649862 | 919.852ms | 8150 | 1280 | 2046.57 | 1945.75 | 0.00349307 | 1.31628 | 5.66429 | 0.953129 | 0.00167868 | 1.67753e-05 | 9.58589e-07 | 1(Win) | true |
| simdjson (ondemand) | 3633.32 | 0.0357742 | 939.925ms | 8150 | 4890 | 2863.9 | 2139.21 | 0.00202046 | 1.4442 | 6.20135 | 0.890798 | 0.0010158 | 1.53312e-05 | 1.38005e-06 | 2(Loss) | true |
