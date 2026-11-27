
----
### Google Maps Response Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10495.3 | 0.37803 | 108.717ms | 11521 | 160 | 2505.9 | 1046.88 | 0.297619 | 0.230212 | 1(Win) | true |
| Glaze | 3558.63 | 0.331834 | 315.055ms | 11521 | 40 | 4198.72 | 3087.5 | 0.403226 | 0.688191 | 2(Loss) | true |
