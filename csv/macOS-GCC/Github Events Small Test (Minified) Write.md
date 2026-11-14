
----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11201.6 | 3.17141 | 19.6019ms | 1996 | 4890 | 142028 | 169.934 | 0.612044 | 1(Win) | true |
| simdjson (reflection) | 9972.7 | 2.95527 | 21.898ms | 1996 | 4890 | 155596 | 190.874 | 2.01518 | 2(Loss) | true |
| Glaze | 2944.82 | 1.47333 | 67.6029ms | 1996 | 2560 | 232191 | 646.4 | 1.1923 | 3(Loss) | true |
