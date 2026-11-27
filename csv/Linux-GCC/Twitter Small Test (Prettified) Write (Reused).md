
----
### Twitter Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17277.1 | 0.102836 | 26.6421ms | 4300 | 1280 | 76.2603 | 237.355 | 0.065214 | 0.127474 | 1(Win) | true |
| Glaze | 4542.97 | 0.0412083 | 93.5416ms | 4300 | 640 | 88.5536 | 902.669 | 0.0623541 | 0.528755 | 2(Loss) | true |
| simdjson (reflection) | 596.763 | 0.057625 | 710.193ms | 4300 | 30 | 470.409 | 6871.73 | 0.183991 | 4.13236 | 3(Loss) | true |
