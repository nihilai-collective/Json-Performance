
----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5014.8 | 0.155226 | 871.797ms | 7932 | 2560 | 14035.5 | 1508.44 | 0.0195552 | 1.04695 | 4.82716 | 0.786813 | 0.00099764 | 1.85168e-05 | 7.92872e-06 | 1(Win) | true |
| simdjson (ondemand) | 4131.93 | 0.0840014 | 902.716ms | 7932 | 4890 | 11564.9 | 1830.76 | 0.00661114 | 1.26793 | 6.07653 | 0.880737 | 0.00159523 | 1.2865e-05 | 3.97035e-06 | 2(Loss) | true |
