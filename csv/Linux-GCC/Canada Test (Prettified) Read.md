
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 22825 | 0.0852068 | 5750.47ms | 5373214 | 320 | 1.17097e+07 | 224504 | 0.00460299 | 0.108455 | 1(Win) | true |
| simdjson (stage-1) | 17336.8 | 0.186577 | 7657.9ms | 5373214 | 40 | 1.21648e+07 | 295573 | 0.00592882 | 0.142789 | 2(Loss) | true |
