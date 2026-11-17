
----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5189.48 | 0.0494251 | 896.794ms | 9739 | 160 | 125.198 | 1789.74 | 0.0108244 | 1.01478 | 4.74176 | 0.742479 | 0.00139773 | 8.9845e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5139.01 | 0.0460201 | 897.433ms | 9739 | 160 | 110.684 | 1807.32 | 0.0197154 | 1.02518 | 4.87227 | 0.696683 | 0.00118082 | 1.0268e-05 | 0 | 2(Loss) | true |
