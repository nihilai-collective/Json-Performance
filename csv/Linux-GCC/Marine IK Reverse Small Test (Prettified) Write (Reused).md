
----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7980.14 | 0.0318661 | 299.55ms | 24893 | 80 | 71.8922 | 2974.86 | 0.0718005 | 0.307488 | 1(Win) | true |
| Glaze | 3894.68 | 0.626632 | 587.569ms | 24579 | 320 | 455156 | 6018.56 | 0.399449 | 0.63279 | 2(Loss) | true |
| simdjson (reflection) | 541.151 | 0.15415 | 4461.71ms | 24893 | 640 | 2.92674e+06 | 43869.1 | 0.979583 | 4.57226 | 3(Loss) | true |
