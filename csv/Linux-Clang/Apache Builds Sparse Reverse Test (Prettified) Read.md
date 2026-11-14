
----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2327.18 | 0.0178954 | 5825.46ms | 124597 | 4890 | 408272 | 51059.7 | 0.0771568 | 2.19461 | 10.4017 | 1.96503 | 0.00551074 | 4.67602e-06 | 1.25066e-06 | 1(Win) | true |
| simdjson (ondemand) | 2079.16 | 0.0585805 | 6418.15ms | 124597 | 640 | 717343 | 57150.5 | 0.0666256 | 2.45406 | 10.3194 | 1.81535 | 0.00649755 | 4.70266e-06 | 1.65534e-06 | 2(Loss) | true |
