
----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 15176.2 | 4.23237 | 21.142ms | 2866 | 2560 | 148742 | 180.1 | 5.50892 | -(Win) | false |
| Glaze | 3084 | 0.599076 | 94.593ms | 2866 | 4890 | 137847 | 886.263 | 1.11987 | 2(Loss) | true |
| simdjson (reflection) | 365.405 | 0.706257 | 765.137ms | 2866 | 160 | 446528 | 7480 | 1.41291 | 3(Loss) | true |
