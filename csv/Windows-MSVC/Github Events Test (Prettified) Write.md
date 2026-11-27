
----
### Github Events Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10296.3 | 0.15387 | 771.639ms | 78778 | 30 | 3781.61 | 7296.67 | 0.0457038 | 0.239234 | 1(Win) | true |
| Glaze | 4264.42 | 0.235888 | 1774.79ms | 78778 | 2560 | 4.42124e+06 | 17617.5 | 0.272201 | 0.579639 | 2(Loss) | true |
