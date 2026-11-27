
----
### Discord Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7087.46 | 0.557435 | 93.1761ms | 7376 | 40 | 1224.36 | 992.5 | 0.0838926 | 0.338208 | 1(Win) | true |
| Glaze | 2976.99 | 0.3191 | 253.169ms | 7376 | 2560 | 145539 | 2362.89 | 0.122185 | 0.820371 | 2(Loss) | true |
