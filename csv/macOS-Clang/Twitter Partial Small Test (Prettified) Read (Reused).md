
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4805.21 | 0.093169 | 81.866ms | 3808 | 2560 | 1269.26 | 755.761 | 0.00449691 | 1(Win) | true |
| Jsonifier (two-stage) | 4673.34 | 0.303104 | 86.9377ms | 3808 | 80 | 443.828 | 777.087 | 0.00160854 | 2(Loss) | true |
| simdjson (ondemand) | 4243.88 | 0.276514 | 91.8496ms | 3808 | 160 | 895.823 | 855.725 | 1.13797 | 3(Loss) | true |
| Glaze | 2688.43 | 0.112555 | 142.474ms | 3808 | 4890 | 11304.1 | 1350.82 | 0.273625 | 4(Loss) | true |
