
----
### Github Events Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13200.8 | 2.81064 | 24.6331ms | 2866 | 4890 | 165606 | 207.051 | 0.0730424 | 1(Win) | true |
| Glaze | 2883.2 | 0.387588 | 96.9311ms | 2866 | 4890 | 66016.6 | 947.985 | 0.536641 | 2(Loss) | true |
| simdjson (reflection) | 395.843 | 0.101243 | 695.38ms | 2866 | 4890 | 238969 | 6904.83 | 0.129772 | 3(Loss) | true |
