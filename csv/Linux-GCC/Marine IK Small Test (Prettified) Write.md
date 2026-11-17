
----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7188.38 | 0.0699885 | 329.106ms | 24579 | 30 | 156.257 | 3260.87 | 0.051085 | 0.341565 | 1(Win) | true |
| Glaze | 3714.13 | 0.256094 | 697.304ms | 24579 | 640 | 167184 | 6311.13 | 0.0522365 | 0.663886 | 2(Loss) | true |
| simdjson (reflection) | 556.017 | 0.160357 | 4381.95ms | 24893 | 4890 | 2.29225e+07 | 42696.2 | 0.776531 | 4.44974 | 3(Loss) | true |
