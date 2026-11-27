
----
### Marine IK Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 902.031 | 0.0868185 | 1942.86ms | 18245 | 4890 | 1.37144e+06 | 19289.6 | 0.0366949 | 1(Win) | true |
| simdjson (ondemand) | 609.575 | 0.113822 | 2864.87ms | 18245 | 2560 | 2.70227e+06 | 28544.1 | 0.0449909 | 2(Loss) | true |
