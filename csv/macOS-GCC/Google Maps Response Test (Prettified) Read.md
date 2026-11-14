
----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6231.44 | 0.395685 | 381.289ms | 25388 | 4890 | 1.15581e+06 | 3885.44 | 1.12626 | 1(Win) | true |
| simdjson (stage-1) DID NOT CONVERGE | 5053.2 | 1.19072 | 497.436ms | 25388 | 1280 | 4.16633e+06 | 4791.4 | 6.05835 | -(Loss) | false |
