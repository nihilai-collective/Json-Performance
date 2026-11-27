
----
### Github Events Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15568.7 | 1.03853 | 523.041ms | 78778 | 80 | 200922 | 4825.6 | 0.919842 | 1(Win) | true |
| Glaze | 2775.14 | 1.91826 | 2591.74ms | 78778 | 40 | 1.07874e+07 | 27072 | 0.517404 | 2(Loss) | true |
| simdjson (reflection) | 393.716 | 0.206316 | 5132.28ms | 78778 | 1280 | 1.9839e+08 | 190819 | 0.631468 | 3(Loss) | true |
