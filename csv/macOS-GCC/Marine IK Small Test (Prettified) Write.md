
----
### Marine IK Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9084.61 | 0.325979 | 265.974ms | 24893 | 4890 | 354837 | 2613.19 | 0.0187303 | 1(Win) | true |
| Glaze | 3130.39 | 1.1239 | 786.067ms | 24579 | 80 | 566596 | 7488 | 0.510204 | 2(Loss) | true |
| simdjson (reflection) | 324.428 | 0.161174 | 7614.02ms | 24893 | 320 | 4.45101e+06 | 73174.4 | 0.124789 | 3(Loss) | true |
