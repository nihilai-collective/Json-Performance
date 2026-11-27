
----
### Github Events Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20143.9 | 0.0895984 | 16.246ms | 2866 | 2560 | 37.836 | 135.685 | 0.136274 | 0.0990487 | 1(Win) | true |
| Glaze | 5304.28 | 0.114665 | 54.4632ms | 2866 | 80 | 27.929 | 515.288 | 0.24441 | 0.441543 | 2(Loss) | true |
| simdjson (reflection) | 596.046 | 0.107759 | 455.08ms | 2866 | 30 | 732.524 | 4585.6 | 0.0283416 | 4.12918 | 3(Loss) | true |
