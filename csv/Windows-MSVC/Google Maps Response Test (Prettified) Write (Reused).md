
----
### Google Maps Response Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11939.1 | 0.28522 | 255.251ms | 31235 | 40 | 2025.64 | 2495 | 0.0667557 | 0.205848 | 1(Win) | true |
| Glaze | 4260 | 0.118854 | 715.347ms | 31235 | 40 | 2762.82 | 6992.5 | 0.0119161 | 0.5791 | 2(Loss) | true |
