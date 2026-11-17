
----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16285.6 | 0.0865507 | 19.593ms | 2866 | 1280 | 27.0082 | 167.831 | 0.205239 | 0.127506 | 1(Win) | true |
| Glaze | 2857.42 | 0.0985788 | 70.5639ms | 2866 | 160 | 142.263 | 956.538 | 0.0117626 | 0.840658 | 2(Loss) | true |
| simdjson (reflection) | 569.702 | 0.16452 | 488.276ms | 2866 | 4890 | 304653 | 4797.65 | 0.0104228 | 4.32016 | 3(Loss) | true |
