
----
### Google Maps Response Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17752.9 | 0.163488 | 64.6588ms | 11521 | 30 | 30.7138 | 618.9 | 0.210492 | 0.133435 | 1(Win) | true |
| Glaze | 5339.33 | 0.130487 | 211.165ms | 11521 | 30 | 216.303 | 2057.8 | 0.224654 | 0.457738 | 2(Loss) | true |
